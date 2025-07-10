#!/bin/bash

generate_unique_ints() {
	local count=${1:-0}
	if [ "$count" -le 0 ]; then
		echo "Usage: $(basename "$0") <value between 0-2147483647>" >&2
		return 1
	fi
	tempfile=$(mktemp)
	while [ $(wc -l < "$tempfile") -lt "$count" ]; do
		random_num=$(openssl rand -hex 4 | awk '{printf "%d", "0x"$1}')
		random_num=$(( random_num % 4294967296 - 2147483648 ))
		if ! grep -q "^$random_num$" "$tempfile"; then
			echo "$random_num" >> "$tempfile"
		fi
	done
	tr '\n' ' ' < "$tempfile"
	rm "$tempfile"
}
generate_unique_ints "$1"
