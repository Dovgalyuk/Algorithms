import matplotlib.pyplot as plt
import csv

n = []
rb_time = []
map_time = []
umap_time = []

with open('results.csv', 'r') as f:
    reader = csv.DictReader(f, delimiter=';')
    for row in reader:
        n.append(int(row['N']))
        rb_time.append(int(row['RBTree_Time']))
        map_time.append(int(row['Map_Time']))
        umap_time.append(int(row['UnorderedMap_Time']))

plt.figure(figsize=(10, 6))
plt.plot(n, rb_time, marker='o', label='My RBTree')
plt.plot(n, map_time, marker='s', label='std::map')
plt.plot(n, umap_time, marker='^', label='std::unordered_map')

plt.title('Benchmark: Insertion Time vs Number of Elements')
plt.xlabel('Number of elements (N)')
plt.ylabel('Time (ms)')
plt.xscale('log')
plt.grid(True)
plt.legend()
plt.savefig('plot.png')
plt.show()