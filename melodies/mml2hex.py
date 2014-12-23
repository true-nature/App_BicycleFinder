#!env python3

import sys
import re
import struct
import binascii

def mml2hex(f):
    txt = ""
    with open(f) as tf:
        for line in tf:
            txt = txt + re.sub("[\u0000-\u0020\u007f-]", "", line)
    length = len(txt)
    if length > 250:
        txt = txt[:250]
        length = 250
    sum = 0x7C + 0x95 + 0x00 + 0x01 + 0x00 + length
    pkt = [":7C95000100", "{0:02X}".format(length)]
    for c in txt:
        sum = sum + ord(c)
        pkt.append("{0:02X}".format(ord(c)))
    chksum = (0x100 - (0xff & sum)) & 0xff
    #pkt.append("{0:02X}".format(chksum))
    pkt.append("X")
    print("".join(pkt))

if __name__ == "__main__":
    for f in sys.argv[1:]:
        mml2hex(f)
