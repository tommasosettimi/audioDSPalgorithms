(
// Number of values to average
~avgBufferSize = 10;
~avgValues = Array.fill(~avgBufferSize, { 0.0 });
~avgCurrentIndex = 0;
~avgCurrentAverage = 0.0;

// Function to calculate the average
~updateAverage = { |newValue|
    // Subtract the oldest value from the current average
    ~avgCurrentAverage = ~avgCurrentAverage - (~avgValues[~avgCurrentIndex] / ~avgBufferSize);

    // Update the array with the new value
    ~avgValues[~avgCurrentIndex] = newValue;

    // Add the new value to the current average
    ~avgCurrentAverage = ~avgCurrentAverage + (newValue / ~avgBufferSize);

    // Increment the index
    ~avgCurrentIndex = (~avgCurrentIndex + 1) % ~avgBufferSize;

    // Output the current average
    ~avgCurrentAverage
};

~heightAverage = ~updateAverage.(1.0)





// Test the average function
Routine.run {
    100.do {
        var newValue = 0.1;
        var average = ~updateAverage.value(newValue);
        [newValue, average].postln;
        0.1.wait;
    }
};
)


