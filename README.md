<h1 align="center">
  <br>
  <img src="https://hackedserver.org/choucroute/triceratops.svg" alt="Poyuterm logo" width="256">
  <br>
</h1>

<h4 align="center">👾 A retro game within terminal.</h4>

<p align="center">
    <a href="https://lgtm.com/projects/g/Th0rgal/poyuterm/context:cpp">
        <img alt="Language grade: C/C++" src="https://img.shields.io/lgtm/grade/cpp/g/Th0rgal/poyuterm.svg?logo=lgtm"/>
    </a>
    <a href="https://lgtm.com/projects/g/Th0rgal/poyuterm/alerts/">
        <img alt="Total alerts" src="https://img.shields.io/lgtm/alerts/g/Th0rgal/poyuterm.svg?logo=lgtm"/>
    </a>
</p>

## Why Poyuterm?
Poyuterm was produced as a duo as a project for the University of Paris Saclay. We had to make a game of PuyoPuyo (a kind of tetrix) and since we didn't want to compete with the beautiful games made with graphic designers, we decided to try to do it in the terminal only.

## Get Poyuterm
#### Required libs and tools:
- cmake
- pkg-config
- ncurses
- doctest
- sfml 

> If you are using nixos, you can just type ``nix-shell`` inside the directory to open a preconfigured shell

#### Compilation
```sh
cmake .
make
```

#### Launching poyuterm
```
# with randomly generated blocks
./poyuterm

# from an input file
./poyuterm file_name

# to solve a game (this will generate a sortie.txt file)
./poyuterm file_name
```