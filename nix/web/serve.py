"""Serves the web build of the game on localhost.

usage: serve-web [PORT] [DIRECTORY]

Unlike `python3 -m http.server`, it tells browsers not to cache
anything. Everything Nix builds is dated 1970, so a server that goes by
file dates would report a rebuilt game as unchanged, and the browser
would go on running the version it cached first.
"""

import functools
import http.server
import sys


class Handler(http.server.SimpleHTTPRequestHandler):
    def end_headers(self):
        self.send_header("Cache-Control", "no-store")
        super().end_headers()


def main(default_root):
    args = sys.argv[1:]
    if "-h" in args or "--help" in args:
        print(__doc__.strip())
        sys.exit(0)
    if len(args) > 2:
        sys.exit(__doc__.strip())
    port = int(args[0]) if args else 8000
    root = args[1] if len(args) > 1 else default_root

    handler = functools.partial(Handler, directory=root)
    with http.server.ThreadingHTTPServer(("127.0.0.1", port), handler) as server:
        print(f"Serving {root} at http://localhost:{port}/", flush=True)
        try:
            server.serve_forever()
        except KeyboardInterrupt:
            pass


if __name__ == "__main__":
    main(sys.argv.pop(1))
