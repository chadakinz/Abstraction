import subprocess

# Loop over i = 0 to 99
for i in range(1000):
    input_file = f"./random_samples/sample_{i}.txt"
    output_file = f"./clusters/output_{i}.txt"

    cmd = [
        "../../wasserstein_kmeanspp/build/bin/pkmeans",
        "-k", "1000",
        "-i", input_file,
        "-o", output_file,
        "-t", "10",
        "-s", "5e-4",
        "-u", "500",
        "-N", "60"
    ]

    print(f"Running pkmeans for i={i}...")
    result = subprocess.run(cmd, capture_output=True, text=True)

    # Optional: print stdout / stderr
    print(result.stdout)
    if result.returncode != 0:
        print(f"Error running pkmeans for i={i}:", result.stderr)