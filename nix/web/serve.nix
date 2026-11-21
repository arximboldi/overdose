# serve-web [PORT [DIRECTORY]]: serves the web build of the game on
# localhost, without letting the browser cache it. `nix run .#serve-web`
# serves the site Nix builds, and the one in `nix develop .#web` serves
# build-web/src.
{
  writeShellApplication,
  python3,
  root,
}:
writeShellApplication {
  name = "serve-web";
  runtimeInputs = [ python3 ];
  text = ''
    exec python3 ${./serve.py} ${root} "$@"
  '';
}
