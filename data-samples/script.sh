#!/bin/bash
cd /opt/goinfre/sparrvio
git clone https://github.com/Homebrew/brew homebrew
eval "$(/opt/goinfre/sparrvio/homebrew/bin/brew shellenv)"
brew update --force --quiet
chmod -R go-w "$(brew --prefix)/share/zsh"

brew install gcov
brew install lcov
# var=s21
# echo "var = $var"