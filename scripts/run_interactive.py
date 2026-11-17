#!/usr/bin/env python3
"""Runs a program inside a pseudo-terminal and feeds it lines of input, so the saved output
shows the typed input after each prompt exactly as it appears in a real console session.
Usage: run_interactive.py <program> <input-file> <output-file>"""
import os, pty, sys, time, select

prog, infile, outfile = sys.argv[1:4]
lines = open(infile).read().splitlines()
pid, fd = pty.fork()
if pid == 0:
    os.execv(prog, [prog])
buf = b""
def drain(wait=0.3):
    global buf
    while True:
        r, _, _ = select.select([fd], [], [], wait)
        if not r: return
        try: chunk = os.read(fd, 4096)
        except OSError: return
        if not chunk: return
        buf += chunk
drain(0.5)
for line in lines:
    os.write(fd, (line + "\n").encode()); drain(0.2)
drain(0.5)
os.waitpid(pid, 0)
open(outfile, "w").write(buf.decode().replace("\r", ""))
