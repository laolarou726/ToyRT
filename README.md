# ToyRT [![CodeQL](https://github.com/laolarou726/ToyRT/actions/workflows/codeql.yml/badge.svg)](https://github.com/laolarou726/ToyRT/actions/workflows/codeql.yml)

A toy QMC Path Tracing Render written in C++. Only for academic purposes.

<div>
  <img width="350" alt="preview" src="https://user-images.githubusercontent.com/25716486/208178836-dac43029-579c-470c-915b-e5b9f11f059d.png">
  <img width="350" alt="preview2" src="https://user-images.githubusercontent.com/25716486/208180053-227f31e7-359d-4ec8-9388-0edb76278c48.png">
</div>

## Special Thanks

[CodingEric](https://github.com/CodingEric), help and technical support was provided during the development.

At the same time, this project is developed based on his open source [CSharpRT](https://github.com/CodingEric/CSharpRT).


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

### Supported Materials

|Material Name|Status|
|:-----------:|:----:|
|   Diffuse   |  ✅  |
|   Reflect   |  ✅  |
|  Dielectric |  ✅  |
|   Emission  |  ✅  |

### Supported Features

|Feature        | Status |
|:-------------:|:------:|
|Basic Scene Manager|✅|
|Basic PT Camera|  ✅  |
|Basic Geometries|✅|
|Anti-aliasing|✅|
|Parallel Render|✅|
|Direct Light Sampling|WIP|
