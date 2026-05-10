#!/bin/bash
../stressor/stressor 4 10 &
../renderer/build/rndr 50000 10 &
wait
