#!/bin/sh

./walk test > test/output

cmp test/ref test/output
