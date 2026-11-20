{
  description = "Overdose, a small 3D game about the effects of drugs";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs =
    { nixpkgs, flake-utils, ... }:
    flake-utils.lib.eachSystem [ "x86_64-linux" "aarch64-linux" ] (
      system:
      let
        pkgs = nixpkgs.legacyPackages.${system};
        overdose = pkgs.callPackage ./nix/package.nix { };
      in
      {
        packages.default = overdose;
        devShells.default = pkgs.callPackage ./nix/devshell.nix { inherit overdose; };
      }
    );
}
