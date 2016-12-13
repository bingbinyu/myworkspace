#! /usr/bin/env bash


# nothing to do if argument list is empty
test $# -gt 0 || exit 0

# Simple logger function.
# Outputs arguments to stderr unless QUIET=1 is specified
function log {
    test ${QUIET:-0} = 1 || echo "$*" >&2
}

# Read ID3 tag from input file and extract given bytes and remove zero
# bytes. (Note that this deletes any zero byte not only trailing.)
function trim_zeroes {
    echo `tail -c128 "$1"|cut -b${2}-${3}|tr -d "\000"`
}

# Convert blank and dash to underscores.
function to_underscore {
    tr ' -' '__'
}

# iterate over argument list
for f in "$@"; do
    if test -f "$f"; then
        log "checking '$f'"
    else
        echo "'$f' is not a reguar file, skipping"
        continue
    fi
        
    # extract ID3 tag and check for magic character sequence
    TAG="`trim_zeroes "$f" 1 3`"
    if test "x$TAG" != "xTAG"; then
        echo "$f has no ID3 tag" >&2
        continue  # not found -> skip this one
    fi

    # now extract title, artist, and album with underscore conversion
    TITLE="`trim_zeroes "$f" 4 33|to_underscore`"
    ARTIST="`trim_zeroes "$f" 34 63|to_underscore`"
    ALBUM="`trim_zeroes "$f" 64 93|to_underscore`"

    # check if byte 125 is zero -> contains on byte track number
    if test "x`trim_zeroes "$f" 125 126`" = "x"; then
        TRACK="`trim_zeroes "$f" 126 127`"
        # use od to convert binary to text, pad to two digits, and
        # add a '-' as prefix
        printf -v TRACK -- "-%02d" `echo -n "$TRACK"|od -t d1 -N1|head -1|cut -d\  -f2-`
    else
        # no track number, leave variable empty
        TRACK=""
    fi
    log "Title is ${TITLE:-_}"
    log "Artist is ${ARTIST:-_}"
    log "Album is ${ALBUM:-_}"
    log "Track is ${TRACK:-not set}"

    # determine directory component to rename file with entire path
    DIR=$(dirname "$f")
    log "mv \""$f"\" ${DIR:-.}/${ARTIST:-_}-${ALBUM:-_}-${TITLE:-_}$TRACK.mp3"
    mv "$f" ${DIR:-.}/${ARTIST:-_}-${ALBUM:-_}-${TITLE:-_}$TRACK.mp3
done
