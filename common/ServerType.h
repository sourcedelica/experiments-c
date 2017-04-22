#pragma once

enum class ServerType { Primary, Backup };

constexpr const char *ServerTypeName(ServerType serverType) {
    return serverType == ServerType::Primary ? "primary" : "backup";
}