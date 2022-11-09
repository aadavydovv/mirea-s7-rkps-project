#!/bin/bash

for dialogue in dialogues/*; do
  cat "$dialogue" | output/run "log/vintbas/$(basename "$dialogue")" > "log/c/$(basename "$dialogue")"
done
