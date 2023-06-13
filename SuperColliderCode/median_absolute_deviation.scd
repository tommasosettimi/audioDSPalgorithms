
/*

Median Absolute Deviation in SuperCollider language.
Useful function to calculate the average of signal without considering outliers.
To be implemented as a SC UGen soon for real-time applications.

*/

(
// Calculate the median
~calculateMedian = { |list|
	var sortedList, medianIndex;
    sortedList = list.sort;
    medianIndex = sortedList.size.div(2);
    sortedList[medianIndex]
};

// Calculate the median absolute deviation (MAD)
~calculateMAD = { |list, median|
	var absDeviations;
    absDeviations = list.collect { |x| (x - median).abs };
    ~calculateMedian.(absDeviations)
};

// Main function to calculate the average without outliers
~calculateAverageWithoutOutliers = { |arr, threshold = 3|
	var sortedArr, median, mad, outliersThreshold, filteredArr;
    sortedArr = arr.sort;
    median = ~calculateMedian.(sortedArr);
    mad = ~calculateMAD.(sortedArr, median);
    outliersThreshold = threshold * mad;
    filteredArr = sortedArr.select { |x| (x - median).abs <= outliersThreshold };
    filteredArr.sum / filteredArr.size
};
)


// EXAMPLE

(
~array = [1,1,1,1,1,1,1,1];
"Original array: ".post; ~array.postln;
"Average of the original array: ".post; (~array.sum / ~array.size).postln;
~array = ~array.add(685); // add an outlier (number 685)
~array = ~array.add(348); // add an outlier (number 348)
"Array with outliers: ".post; ~array.postln;
"Average of the array with outliers: ".post;
~average = ~calculateAverageWithoutOutliers.(~array);
~average.postln;
"Same average as the array with the outliers".postln;
)





