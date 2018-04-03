# Operating Systems Competition

## Context Setting

Unfortunately, when the spaceship crashed, the penguins lost their git repository containing the middleware (user space communicating with kernel space) library able to read and write the spaceship's black box.

Since the penguins are kind of stubborn against changes and not very up-to-date, they were self-hosting their repo on the spaceship.

The so-called black box, called "`kiki`", is a capricious device (very unstable) using a not so common (not common at all) driver interface.

It is mandatory for the penguins to reproduce a working implementation of the library, the one lost along their repository, in order to someday be able to retrieve the crucial information recorded during the flight.


## Main Goal

Reproduce a working implementation of the `libkiki_api` middleware library, which must be able to communicate with the `kiki` device driver.

The implementation __must meet every__ requirement and specification presented in the documentation, which is available in the system's UNIX manual entries.


## Requirements

- The __whole__ source must be implemented in the C language. No C++ or any other language will be accepted.
- Any dependency, in terms of library, is __illegal__.
- The library should be able to be compiled statically (`.a` archive).
- It is mandatory to meet the delivery format explained in the "Deliverable" section.

__Not meeting every requirement__ will result in a __0% score__.


## Directives

All the necessary documentation for the competition is available on the system in the UNIX manual entries:

- `kiki` entry for the device's documentation and its kernel calling interface.
- `name_of_the_function_to_implement` entry for the per-function-to-implement documentation.

You will find the __kernel calling interface__ in the `kiki.h` header, installed in `/usr/include`.

You will find the __list of functions to implement__ in the `kiki_api.h` header, installed int `/usr/include`.


## Deliverable

__Each function__ whose declaration is present in `kiki_api.h` must be implemented in __a single__ source file named `kiki_api.c`.

This source file (`kiki_api.c`) must then be shipped.


## Bonuses

- A mystery bonus shall be granted to any implementation compiling without any warning in the C89 standard.
