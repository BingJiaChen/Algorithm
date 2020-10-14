list="IS QS MS HS"

for s in $list;do
    ./bin/NTU_sort -$s ./inputs/4000.case2.in ./outputs/4000.case.out
    diff ./inputs/4000.case2.in ./outputs/4000.case.out
    echo "$s 4000_case2 completed."
    echo "--------------------------------"
    ./bin/NTU_sort -$s ./inputs/4000.case3.in ./outputs/4000.case.out
    diff ./inputs/4000.case2.in ./outputs/4000.case.out
    echo "$s 4000_case3 completed."
    echo "--------------------------------"
    ./bin/NTU_sort -$s ./inputs/4000.case1.in ./outputs/4000.case.out
    diff ./inputs/4000.case2.in ./outputs/4000.case.out
    echo "$s 4000_case1 completed."
    echo "--------------------------------"

    ./bin/NTU_sort -$s ./inputs/16000.case2.in ./outputs/16000.case.out
    diff ./inputs/16000.case2.in ./outputs/16000.case.out
    echo "$s 16000_case2 completed."
    echo "--------------------------------"
    ./bin/NTU_sort -$s ./inputs/16000.case3.in ./outputs/16000.case.out
    diff ./inputs/16000.case2.in ./outputs/16000.case.out
    echo "$s 16000_case3 completed."
    echo "--------------------------------"
    ./bin/NTU_sort -$s ./inputs/16000.case1.in ./outputs/16000.case.out
    diff ./inputs/16000.case2.in ./outputs/16000.case.out
    echo "$s 16000_case1 completed."
    echo "--------------------------------"

    ./bin/NTU_sort -$s ./inputs/32000.case2.in ./outputs/32000.case.out
    diff ./inputs/32000.case2.in ./outputs/32000.case.out
    echo "$s 32000_case2 completed."
    echo "--------------------------------"
    ./bin/NTU_sort -$s ./inputs/32000.case3.in ./outputs/32000.case.out
    diff ./inputs/32000.case2.in ./outputs/32000.case.out
    echo "$s 32000_case3 completed."
    echo "--------------------------------"
    ./bin/NTU_sort -$s ./inputs/32000.case1.in ./outputs/32000.case.out
    diff ./inputs/32000.case2.in ./outputs/32000.case.out
    echo "$s 32000_case1 completed."
    echo "--------------------------------"

    ./bin/NTU_sort -$s ./inputs/1000000.case2.in ./outputs/1000000.case.out
    diff ./inputs/1000000.case2.in ./outputs/1000000.case.out
    echo "$s 1000000_case2 completed."
    echo "--------------------------------"
    ./bin/NTU_sort -$s ./inputs/1000000.case3.in ./outputs/1000000.case.out
    diff ./inputs/1000000.case2.in ./outputs/1000000.case.out
    echo "$s 1000000_case3 completed."
    echo "--------------------------------"
    ./bin/NTU_sort -$s ./inputs/1000000.case1.in ./outputs/1000000.case.out
    diff ./inputs/1000000.case2.in ./outputs/1000000.case.out
    echo "$s 1000000_case1 completed."
    echo "--------------------------------"
done
