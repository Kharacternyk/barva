{ pkgs ? import <nixpkgs> { } }:

pkgs.python3Packages.buildPythonPackage rec {
  name = "barva";
  src = ./.;
  propagatedBuildInputs = with pkgs; [
    libpulseaudio
    ncurses
    python3Packages.numpy
  ];
  nativeBuildInputs = with pkgs; [
    python3Packages.pytest
    python3Packages.hypothesis
  ];

  BARVA_PULSE_SIMPLE = "${pkgs.libpulseaudio}/lib/libpulse-simple.so.0";
}
