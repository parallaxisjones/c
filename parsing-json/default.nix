# default.nix
{ pkgs ? import <nixpkgs> {} }:

let
  jansson = pkgs.jansson;
in
pkgs.stdenv.mkDerivation {
  pname = "simple-parse-example";
  version = "1.0";

  src = ./.;

  nativeBuildInputs = [ pkgs.clang ];
  buildInputs = [ jansson ];

  buildPhase = ''
    clang -g -Wall -o simple-parse-example simple-parse-example.c -ljansson
  '';

  installPhase = ''
    mkdir -p $out/bin
    cp simple-parse-example $out/bin/
    rm simple-parse-example
  '';

  meta = with pkgs.lib; {
    description = "A simple program using jansson";
    license = licenses.mit;
    maintainers = [ maintainers.yourname ];
    platforms = platforms.unix;
  };
}
