#!/bin/bash

for dialogue in dialogues/*; do
  cat "$dialogue" | ../output/run "../output/log/vintbas/$(basename "$dialogue")" > "../output/log/c/$(basename "$dialogue")"
done
