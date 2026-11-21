{
  mkShell,
  clang-tools,
  overdose,
}:
mkShell {
  inputsFrom = [ overdose ];
  # clang-format, for the style in .clang-format.
  packages = [ clang-tools ];
}
