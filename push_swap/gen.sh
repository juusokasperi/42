#!/bin/bash

generate_unique_ints() {
	RANDOM=$(date +%s)
	tempfile=$(mktemp)
	while [ $(wc -l < "$tempfile") -lt 500 ]; do
		random_num=$((RANDOM * RANDOM - 2**31))
		if ! grep -q "^$random_num$" "$tempfile"; then
			echo "$random_num" >> "$tempfile"
		fi
	done
	tr '\n' ' ' < "$tempfile"
	rm "$tempfile"
}
generate_unique_ints
