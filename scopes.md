# Config

Config is composed of a number of features:

1. A hierarchical list of configurations called Scopes.
2. Individual configuration files in
   [HOCON](https://github.com/lightbend/config/blob/master/HOCON.md)
   format.
3. The Config API

Config has been used successfully in many projects at Nomura.

## Scopes

A scopes definition determines the set of configuration files used by an
application.

A configuration for an application is defined as a hierarchical list of
configurations. For example, the configuration for the Report Service
would be defined by this stack of configurations:

- Report Service
- Report Service - Environment specific
- Report Service - AppID specific
- Base Service
- Base Service - Environment specific
- Data Client
- Data Client - Environment specific
- Login Client
- Login Client - Environment specific

All of the configuration files are merged together, with values in files
lower in the list overriding values with the same key in higher-level
files.

In this example, the Report Service configuration contains all of the
properties specific to that application.

Environment-specific configurations contain _only_ the properties that
are needed for that enviroment (for example, hostnames, ports, etc).

Configurations for specific libraries or clients are defined in one
place and reused across multiple applications. This avoids having client
or library-specific properties duplicated across multiple applications.

Here is what the scopes definition would look like for the Report
Service applcation that we have been discussing:

```
scopes = [
    {
        name = report-application
        path = "file://config/report-service.conf"
    }
    {
        name = report-environment
        path = "http://git-config-${environment}/config/report/report-${environment}.conf"
    }
    {
        name = report-appId
        path = "http://git-config-${environment}/config/report/report-${appId}.conf"
    }
    {
        name = base-service
        path = "http://git-config-dev/config/base/base-service.conf"
    }
    {
        name = base-service-environment
        path = "http://git-config-${environment}/config/base/base-service-${environment}.conf"
    }    
    {
        name = data-client
        path = "http://git-config-dev/config/data/data-client.conf"
    }
    {
        name = data-client-environment
        path = "http://git-config-${environment}/config/data/data-client-${environment}.conf"
    }
    {
        name = login-client
        path = "http://git-config-dev/config/login/login-client.conf"
    }
    {
        name = login-client-environment
        path = "http://git-config-${environment}/config/login/login-client-${environment}.conf"
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

For example, let's say that Puneet wants to override
`report.some-timeout` to 10 seconds.

The main Report Service configuration
`file://config/report-service.conf` would look like:

```
report {
    service {
        description: "..."
        max-lines: 200
        some-timeout: 30s
    }
}
```

The configuration file that Puneet manages in Production,
`http://git-config-prod/config/report/report-prod.conf` could look like:

```
report.service.some-timeout = 10s
```

In the Report Service application it would use the Config API to get the
property like:

```
auto someTimeout = config.getDuration("report.service.some-timeout");
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
$ report-service -Dreport.service.some-timeout=15s
```

Then the value of `report.service.some-timeout` would be 15 seconds.

System properties can be used any time, but they are especially useful
during development. Using system properties allows you to set values
temporarily without accidentally committing the changes to the real
configuration file. Use CLion's Run Configuration feature to create
multiple runtime configurations with different system properties set.

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

