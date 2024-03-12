#!/bin/bash

function_add() {
    a=1
    b=2
    return $((a + b))
}

function_add
result=$?

echo "The result of adding a and b is: $result"

