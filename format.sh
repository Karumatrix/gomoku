#!/ usr / bin / env bash

grep_str = "^.*.[cpp|hpp]$"

    all_client_file = "$(find " $
{
    PWD
}
" -maxdepth 5 -type f -not -path '*/\.*' | grep " $grep_str ")" clang - format - i $all_client_file
