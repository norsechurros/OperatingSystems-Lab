#!/bin/sh

echo "Enter upper and lower bound"

read a b

for((i=a;i<=b;i++));do
	for((j=1;j<=i;j++));do
		if [  
