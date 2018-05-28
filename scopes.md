# Config

Config is composed of a number of features:

1. A hierarchical list of configurations called Scopes.
2. Individual configuration files in
   [HOCON](https://github.com/lightbend/config/blob/master/HOCON.md)
   format.
3. The Config API

Config is based on a successful library called Kozo Config.

## Scopes

A scopes definition determines the set of configuration files used by an
application.

A configuration for an application is defined as a hierarchical list of
configurations. For example, the configuration for the Report Service
would be defined by this stack of configurations:

- Report Service
- Logging
- Base Service
- Data Client
- Login Client
- Environment-specific
- AppID-specific

All of the configuration files are merged together, with values in files
lower in the list overriding values with the same key in higher-level
files.

In this example, the Report Service configuration contains all of the
properties specific to that application.

Configurations for specific libraries or clients are defined in one
place and reused across multiple applications. This avoids having client
or library-specific properties duplicated across multiple applications.

Environment-specific and AppID-specific configurations contain _only_ the properties that
are needed for that enviroment (for example, hostnames, ports, etc).

Here is what the scopes definition would look like for the Report
Service applcation that we have been discussing:

```
scopes = [
    {
        name = report-service
        path = "file://config/report-service.conf"
    }
    {
        name = logging
        path = "http://git-config-dev/config/logging/logging.conf"
    }
    {
        name = base-service
        path = "http://git-config-dev/config/base/base-service.conf"
    }
    {
        name = data-client
        path = "http://git-config-dev/config/data/data-client.conf"
    }
    {
        name = login-client
        path = "http://git-config-dev/config/login/login-client.conf"
    }
    {
        name = per-environment
        path = "http://git-config-${environment}/config/environment/${environment}.conf"
    }
    {
        name = per-appId
        path = "http://git-config-${environment}/config/appId/${appId}.conf"
    }
]
```

Each configuration lives at a particular URL. A `file://` path refers to
a file that is relative to the application installation, just like our
existing JSON configuration files. An `http://` path is served by a HTTP
server.

In our case the HTTP paths are served from a Git server like Bitbucket.
This way each configuration is version controlled. The Git config server
in Development is different from the one in QA/Prod. This way Puneet's
team can manage their own environment-specific configurations.

Client configurations are managed by the team that own the specific
service. This way the team that manages a client configuration can
release an updated configuration without needing to coordinate with
other applications.

### Selecting the Scopes Definition

The Scopes definition is selected when creating the configuration. For
example:

```
auto config = Config::loadConfig("file://config/report-scopes.conf")
```

You can override the default scopes configuration on the command line
using the syntax `-Dconfig.scopes=path`. For example:

```
$ report-service -Dconfig.scopes=file://config/other-report-scopes.conf
```

### Overriding

Properties in configurations at a lower level in the scopes definition
override corresponding properties defined in a higher level
configuration.

For example, let's say that Puneet wants to override the property
`report.service.someTimeout` to 10 seconds.

The main Report Service configuration
`file://config/report-service.conf` might look like:

```
report {
    service {
        description: "..."
        maxLines: 200
        someTimeout: 30s
    }
}
```

The configuration file that Puneet manages in Production,
`http://git-config-prod/config/environent/prod.conf` might look like:

```
report.service.someTimeout = 10s
```

In the Report Service application it would use the Config API to get the
property like:

```
auto someTimeout = config.getDuration("report.service.someTimeout");
```

In development the value of `someTimeout` would be 30 seconds. In
Production the value of `someTimeout` would be 10 seconds.

### System Properties

System Properties are properties that are passed on the command line.
The syntax for passing system properties is `-Dkey=value`. You can pass
multiple system properties on the command line, eg. `-Dkey1=value1
-Dkey2=value2`

System properties take priority over all configuration scopes. For
example, if the Report Service was started like this:

```
$ report-service -Dreport.service.someTimeout=15s
```

Then the value of `report.service.someTimeout` would be 15 seconds.

System properties can be used any time, but they are especially useful
during development. Using system properties allows you to set values
temporarily without accidentally committing the changes to the real
configuration file.

## HOCON

[HOCON](https://github.com/lightbend/config/blob/master/HOCON.md)
(Human-Optimized Config Object Notation) is a superset of JSON that is
specifically designed for configurations.

HOCON was originally used in a configuration library called Typesafe
Config, which is used by the Akka actor toolkit and the Play Web
Framework.

### Improvements over JSON

You can use pure-JSON for HOCON configurations, but you can also use a
more human-readable syntax as well. You can also export configurations
or portions of configurations into pure JSON.

### hocon-cpp

The HOCON implementation that we will be using is
[cpp-hocon](https://github.com/puppetlabs/cpp-hocon), an implementation
of the HOCON spec in C++.

## Config API

The Config API is an extension of the existing `coreull::Config` API,
adding support for Config Scopes, System Properties and HOCON (it wraps hocon-cpp).

