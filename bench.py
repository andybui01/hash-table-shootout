import sys, os, subprocess, signal

programs = [
    # 'std_unordered_set',
    # 'google_dense_hash_set',
    # 'google_sparse_hash_set',
    'tsl_robin_set',
    'bloom_filter',
]

minkeys  = 250000
maxkeys  = 1000000
interval = 250000
best_out_of = 1

outfile = open('output', 'w')

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
                # 'read_small_string',
                # 'read_miss_small_string',
                    
                'insert_string',
                # 'read_string',
                'read_miss_string',
                )


for nkeys in range(minkeys, maxkeys + 1, interval):
    for benchtype in benchtypes:
        for program in programs:
            
            fastest_attempt = 1000000
            fastest_attempt_data = ''

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

                line = ",".join(map(str, [
                    benchtype,
                    nkeys,
                    program,
                    memory_usage_bytes,
                    "%0.1f" % (runtime_seconds*1000),
                    false_count
                    ]))

                if runtime_seconds < fastest_attempt:
                    fastest_attempt = runtime_seconds
                    fastest_attempt_data = line

            if fastest_attempt != 1000000:
                outfile.write(fastest_attempt_data)
                print(fastest_attempt_data)
        
        # Print blank line
        outfile.write("\n")
