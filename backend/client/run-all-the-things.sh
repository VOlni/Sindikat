#!/bin/bash

../dist/drachtio &
java -jar TadHack/target/CUP-0.0.jar &
./udpcl
echo "Hvala na paznji."
