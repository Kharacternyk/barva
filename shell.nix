{ pkgs ? import <nixpkgs> { } }:

pkgs.python3Packages.buildPythonPackage rec {
  name = "barva";
  src = ./.;
  propagatedBuildInputs = with pkgs; [
    libpulseaudio
    ncurses
    python3Packages.numpy
  ];

  BARVA_PULSE_SIMPLE = "${pkgs.libpulseaudio}/lib/libpulse-simple.so.0";
}
