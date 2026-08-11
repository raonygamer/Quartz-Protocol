# Quartz Protocol

> Shared protocol definitions for communication between Quartz firmware and host software.

Quartz Protocol defines the common RPC protocol used by Quartz firmware and its companion client.

It contains packet definitions, protocol constants, versioning information, profiling identifiers, and other structures
that need to remain consistent between the device and host.

The project is intentionally kept lightweight and freestanding-friendly so the same definitions can be compiled directly
into both embedded firmware and desktop applications.

This is a **personal project written for my own hardware and software**. It's public because someone else might find the
code useful or interesting, but it is **not intended to be a general-purpose device protocol or compatibility layer**.

I make no guarantees about supporting third-party firmware, clients, devices, or maintaining compatibility with software
outside the Quartz projects I personally use.

## Goals

- Single source of truth for the Quartz protocol
- Shared packet definitions between firmware and client
- Modern C++
- Freestanding-friendly
- No dynamic allocation
- Minimal dependencies
- Explicit and predictable binary layouts
- Protocol versioning and compatibility checks
- Lightweight enough for embedded targets

## Protocol

Quartz uses a custom USB RPC protocol for communication between firmware and host software.

The protocol is used for features such as:

- Device identification
- RGB control
- Performance statistics
- Profiling
- Device configuration
- Calibration
- Diagnostics
- Firmware commands

Packet structures are shared directly between the firmware and client wherever possible, avoiding duplicated protocol
definitions and keeping both sides in sync.

## Handshake and Versioning

Before normal RPC communication begins, the client and device perform a stable handshake.

The handshake exposes the protocol version implemented by the device, allowing incompatible clients and firmware to
detect each other before attempting to exchange normal packets.

The handshake format is intended to remain stable even as the rest of the protocol evolves.

Protocol versions may distinguish between compatible additions and breaking changes.

A client should never assume that an unknown protocol version is compatible.

Future versions may also expose capabilities so clients can determine which optional features are supported by a
particular firmware build.

## Binary Layout

Structures intended to be transmitted over the wire use explicitly defined integer sizes and validated layouts.

For example:

```cpp
struct [[gnu::packed]] PacketHeader
{
    std::uint32_t Magic;
    std::uint8_t Version;
    PacketType Type;
    PacketDirection Direction;
    std::uint16_t PayloadLength;
};

static_assert(sizeof(PacketHeader) == 10);
