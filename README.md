# Kinect Based Re-identification framework

This project was part of my computer vision assignment at the university. The aim was to experiment and learn with the Kinect SDK and developer tools, and to set up a simple environment for re-identification.

You can see a [demonstration video](https://youtu.be/JN6Dae-F0i4) of the project on Youtube.

You can also download a [brief report](http://www.davideabati.com/resources/kinect_reid.pdf) brief report, but only in italian :(

### How does it work?
If you took a look at the video above, you probably already noticed that depth information is used to segment the person's body in different parts. In particular:
* pixels belonging to the person's body are assigned to one out of 20 possible skeleton joints, using a nearest neighbours rule;
* color histograms are evaluated for every body part, and get normalized;
* a global histogram is found by concatenation of the local descriptors, and gets normalized as well;
* the final decision about the reidentification is taken by comparison of such descriptor with the previously stored ones, with a thresholded nearest neighbor rule.

### Dependencies and setup
To run the code, you need to install three dependencies:
* OpenCV (2.4 or superior recommended);
* Qt (5.5 recommended);
* Kinect for Windows SDK (1.8 or superior recommended).

In order to run the code, just setup the your favourite IDE including the code and such libraries. Additionally, you need to edit the settings.ini file, that contains all the initial information needed by the software, including
* the type of acquisition (live Kinect or file system);
* the distance used for histogram comparison;
* the type of normalization for local color histograms;
* the type of normalization for the global histogram;
* the number of bins used for the local histograms;
* the thresholds used for recognition (defined for each distance metric);
* the joints you want to involve in the comparison.

If you choose from file acquisition, please stick to the file structure shown in the provided dataset folder and provide a rgb image, a depth image, a player index image and a binary file containing the serialized skeleton frames for each frame.
