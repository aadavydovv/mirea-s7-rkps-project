#!/bin/bash

for dialogue in dialogues/*; do
  cat "$dialogue" | vintbas misc/source.bas > "../output/log/vintbas/$(basename "$dialogue")"
done
