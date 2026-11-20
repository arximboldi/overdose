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
        overdose-web = pkgs.callPackage ./nix/web { };
      in
      {
        packages.default = overdose;
        packages.web = overdose-web;
        devShells.default = pkgs.callPackage ./nix/devshell.nix { inherit overdose; };
        devShells.web = pkgs.callPackage ./nix/web/devshell.nix { inherit overdose-web; };
      }
    );
}
