total_time = 0
samples = 0

with open("output") as f:
	for line in f:
		words = line.split()
		if "Detection" in words:
			total_time += float(words[words.index("Detection") + 2])
			samples += 1

avg = (total_time / samples)
print "Object detection algorithm: frcnn"
print "\tAverage time to detect targets (s):", avg
print "\tFPS:", 1/avg
