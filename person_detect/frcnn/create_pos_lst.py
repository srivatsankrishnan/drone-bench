import argparse

parser = argparse.ArgumentParser(description='Object detection benchmark.')
parser.add_argument('--data',
                   help="Location of dataset. Default: .")
parser.add_argument('--max_samples',
                   help="Maximum number of samples to test. Default: 1000")
args = parser.parse_args()

dataset = args.data if args.data is not None else "."
max_samples = int(args.max_samples) if args.max_samples is not None else 1000

if dataset[-1] == "/":
	dataset = dataset[0:-1]

frcnn_inputs = ""
with open("{}/dataset/pos.lst".format(dataset)) as pos_lst:
	samples = 0

	for image_name in pos_lst:
		if dataset[0] != "/":
			frcnn_inputs += "../{}/{}".format(dataset, image_name)
		else:
			frcnn_inputs += "{}/{}".format(dataset, image_name)

		samples += 1

		if samples >= max_samples:
			break

frcnn_inputs_file = open("py-faster-rcnn/frcnn_pos.lst", "w")
frcnn_inputs_file.write(frcnn_inputs)
frcnn_inputs_file.close()
