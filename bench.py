import sys, os, subprocess, signal

programs = [
    'std_unordered_set',
    'google_dense_hash_set',
    'google_sparse_hash_set',
    'tsl_robin_set',
    'bloom_filter',
]

minkeys  = 250000
maxkeys  = 3000000
interval = 250000
runs = 5


if len(sys.argv) > 1:
    benchtypes = sys.argv[1:]
else:
    benchtypes = (
                # 'insert_random_shuffle_range',
                # 'read_random_shuffle_range',
                # 'insert_random_full',
                # 'read_random_full',
                # 'read_miss_random_full',

                # 'insert_small_string',
                'read_small_string',
                # 'read_miss_small_string',

                # 'insert_string',
                # 'read_string',
                # 'read_miss_string',
                )

# outfile.write("benchtype nkeys table mem time errors\n")
for benchtype in benchtypes:
    outfile = open("data/"+benchtype, 'w')



    # write header
    outfile.write("n,")
    outfile.write(",".join(programs))
    outfile.write("\n")

    for nkeys in range(minkeys, maxkeys + 1, interval):

        timing = []
        mem = []

        for program in programs:

            timing_avg = 0
            memory_avg = 0

            for attempt in range(runs):
                try:
                    output = subprocess.check_output(['./build/' + program, str(nkeys), benchtype])
                    words = output.strip().split()

                    runtime_ms = int(float(words[0]) * 1000)
                    mem_usage = int(words[1])
                    false_count = int(words[2])
                except:
                    print("Error with %s" % str(['./build/' + program, str(nkeys), benchtype]))
                    break

                timing_avg += runtime_ms
                memory_avg += mem_usage

            timing_avg = timing_avg / runs
            memory_avg = memory_avg / runs

            timing.append(str(int(timing_avg)))
            mem.append(str(int(memory_avg)))

        output_list = timing + mem
        string = str(nkeys) + "," + ",".join(output_list) + "\n"

        outfile.write(string)
        print(string)

outfile.close()
