[![License: GPL v3](https://img.shields.io/badge/License-GPL%20v3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)

# Rshell
#### Written By

* Patrick Tumbucon ([Github](https://www.github.com/ptumb001))
* Andrew To ([Github](https://www.github.com/andrew-t187))

## Introduction

Rshell is a command line interface written in C++. It will execute bash-like commands with support for connectors (||, &&, ;) and comments (#). 

## Usage

Clone the repository to your computer.

`git clone https://github.com/cs100/rshell-sudo-rm-rf.git`

Navigate to the cloned directory.

`cd rshell-sudo-rm-rf`

Compile and run.

`make`

`bin/rshell`

## Design

<a href="https://ibb.co/mptPoG"><img src="https://preview.ibb.co/n632aw/Screen_Shot_2017_11_03_at_12_34_15_PM.png" alt="Screen_Shot_2017_11_03_at_12_34_15_PM" border="0" width="550px" margin="0 auto"></a>

We will be using a composite design strategy where “cmd” and “connector” act as composite classes. "exit", "||", "&&", and ";" are the leaves in this project that inherit from the composites. User interface and expression parsing is done in the main file with the Boost C++ library.

## Features

* Single /bin commands with argument flags
* File/Directory testing
* Multiple commands linked with connectors.
* Git support 
* Commands with comments appended after a '#'

## Missing Functionalities

* Precedence operator support

## Bugs

* ~~Comments are parsed as arguments when a space does not follow the '#'~~
