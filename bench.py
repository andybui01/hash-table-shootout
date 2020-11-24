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
best_out_of = 5


if len(sys.argv) > 1:
    benchtypes = sys.argv[1:]
else:
    benchtypes = (
                # 'insert_random_shuffle_range',
                # 'read_random_shuffle_range', 
                # 'insert_random_full',
                # 'read_random_full',
                # 'read_miss_random_full', 

                'insert_small_string',
                # 'read_small_string',
                # 'read_miss_small_string',
                    
                # 'insert_string',
                # 'read_string',
                # 'read_miss_string',
                )

# outfile.write("benchtype nkeys table mem time errors\n")
for benchtype in benchtypes:
    outfile = open("data/"+benchtype+"_mem", 'w')



    # write header
    outfile.write("n,")
    outfile.write(",".join(programs))
    outfile.write("\n")

    for nkeys in range(minkeys, maxkeys + 1, interval):
        string = str(nkeys)
        for program in programs:
            
            fastest_attempt = 1000000
            fastest_attempt_data = ''
            memory_avg = 0

            for attempt in range(best_out_of):
                try:
                    output = subprocess.check_output(['./build/' + program, str(nkeys), benchtype])
                    words = output.strip().split()
                    
                    runtime_seconds = float(words[0])
                    memory_usage_bytes = int(words[1])
                    false_count = int(words[2])
                except:
                    print("Error with %s" % str(['./build/' + program, str(nkeys), benchtype]))
                    break

                if runtime_seconds < fastest_attempt:
                    fastest_attempt = runtime_seconds

            string += ",{}".format(str(memory_usage_bytes))

        outfile.write(string + "\n")
        print(string)

outfile.close()