#!/bin/bash
../stressor/stressor 8 10 &
nice -n -10 ../renderer/build/rndr 50000 10 &
wait
