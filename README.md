# ToyRT [![CodeQL](https://github.com/laolarou726/ToyRT/actions/workflows/codeql.yml/badge.svg)](https://github.com/laolarou726/ToyRT/actions/workflows/codeql.yml)

A toy QMC Path Tracing Render written in C++. Only for academic purposes.

## Special Thanks

[CodingEric](https://github.com/CodingEric/CSharpRT), help and technical support was provided during development.

At the same time, this project is developed based on its open source [CSharpRT](https://github.com/CodingEric/CSharpRT).


## Environment Setup

Tested environment: Ubuntu 22.04.1 LTS

### Install Intel OneAPI

```bash

sudo apt update
sudo apt -y install cmake pkg-config build-essential

```

Add Intel OneAPI Repo Pub Key

```bash

# use wget to fetch the Intel repository public key
wget https://apt.repos.intel.com/intel-gpg-keys/GPG-PUB-KEY-INTEL-SW-PRODUCTS.PUB

# add to your apt sources keyring so that archives signed with this key will be trusted.
sudo apt-key add GPG-PUB-KEY-INTEL-SW-PRODUCTS.PUB

# remove the public key
rm GPG-PUB-KEY-INTEL-SW-PRODUCTS.PUB

```

Config Apt client

```bash

sudo add-apt-repository "deb https://apt.repos.intel.com/oneapi all main"

```

Install OneAPI Libraries

```bash

sudo apt install intel-basekit
sudo apt install intel-hpckit

```

## Features

|Feature        | Status |
|:-------------:|:------:|
|Basic Scene Manager|✅|
|Basic PT Camera|  ✅  |
|Basic Geometries|✅|
|Parallel Render|✅|
|Direct Light Sampling|WIP|
