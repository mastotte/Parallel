# Create a loop that is semantically equivalent to the reference loop.
# That is, it computes  a[0] = a[0] + a[1] + a[2] + a[3] + a[4] ... + a[size]
# where size is passed in by the main source string.
#
# You should unroll by a factor of "partitions". This is done logically
# by splitting a into N partitions (where N == partitions). You will compute
# N reductions, one computation for each partition per loop iteration.
#
# You will need a cleanup loop after the main loop to combine
# the values in each partition.
#
# You can assume the size and the number of partitions will be
# a power of 2, which should make the partitioning logic simpler.
#
# You can gain confidence in your solution by running the code with
# several power-of-2 unroll factors, e.g. 2,4,8,16. You can assume
# partition is less than size.
def homework_reduction_source(partitions):
    # header
    function = "void homework_reduction(reduce_type *a, int size) {"

    # implement me!
    function_body = ""
    function_body = f"\n  int partition_size = size / {partitions};"
    function_body += f"\n  for (int p = 0; p < {partitions}; ++p) {{"
    function_body += f"\n    for (int i = (p * partition_size) + 1 ; i < (p + 1) * partition_size; ++i) {{"
    function_body += f"\n      a[p*partition_size] += a[i+(p*partition_size)];"
    function_body += "\n    }"
    function_body += "\n  }"
    function_body += f"\n  for (int i = 1; i < {partitions}; ++i) {{"
    function_body += "\n    a[0] += a[i * partition_size];"
    function_body += "\n}"
    # closing brace
    function_close = "\n}"
    return "\n".join([function, function_body,function_close])
