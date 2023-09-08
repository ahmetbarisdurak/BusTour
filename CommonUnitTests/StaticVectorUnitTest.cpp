#include <StaticVectorLibrary.h>
#include <StaticVectorIterator.h>
#include <gtest/gtest.h>

class StaticVectorTest : public ::testing::Test {
protected:
	void SetUp() override {
	}

	void TearDown() override {
	}

};

// Test case for PushBack and GetSize methods
TEST_F(StaticVectorTest, PushBackAndGetSize) {
	StaticVector<int, 5> staticVector;

	staticVector.PushBack(1);
	staticVector.PushBack(2);

	EXPECT_EQ(staticVector.GetSize(), 2);
}

// Test case for PushBack which checks whether the correct value has been pushed or not
TEST_F(StaticVectorTest, PushBackCorrectValue) {
	StaticVector<int, 5> staticVector;

	EXPECT_TRUE(staticVector.PushBack(1));
	EXPECT_EQ(staticVector.GetSize(), 1);
	EXPECT_EQ(staticVector.Last(), 1);
}

// Test case for PushBack exceeding capacity
TEST_F(StaticVectorTest, PushBackExceedingCapacity) {
	StaticVector<int, 2> staticVector;  // Capacity set to 2

	EXPECT_TRUE(staticVector.PushBack(1));
	EXPECT_TRUE(staticVector.PushBack(2));
	EXPECT_FALSE(staticVector.PushBack(3));  // Should fail since out of capacity
	EXPECT_EQ(staticVector.GetSize(), 2);
	EXPECT_EQ(staticVector.Last(), 2);
}

// Test case for PopBack and GetSize methods
TEST_F(StaticVectorTest, PopBackAndGetSize) {
	StaticVector<int, 5> staticVector;

	staticVector.PushBack(1);
	staticVector.PushBack(2);
	staticVector.PopBack();

	EXPECT_EQ(staticVector.GetSize(), 1);
}

// Test case for PopBack whether correct value has been popped
TEST_F(StaticVectorTest, PopBackCorrectValue) {
	StaticVector<int, 5> staticVector;

	staticVector.PushBack(1);
	staticVector.PushBack(2);
	staticVector.PopBack();

	EXPECT_EQ(staticVector.Last(), 1);
	EXPECT_EQ(staticVector.GetSize(), 1);
}

// Test case for PopBack when there is no element
TEST_F(StaticVectorTest, PopBackCapacity) {
	StaticVector<int, 2> staticVector;  // Capacity set to 2

	staticVector.PushBack(1);
	staticVector.PushBack(2);
	staticVector.PopBack();
	staticVector.PopBack();


	EXPECT_FALSE(staticVector.PopBack());
}

// Test case for First and Last methods
TEST_F(StaticVectorTest, FirstAndLastTest) {
	StaticVector<int, 5> staticVector;

	staticVector.PushBack(1);
	staticVector.PushBack(2);
	staticVector.PushBack(3);

	EXPECT_EQ(staticVector.First(), 1);
	EXPECT_EQ(staticVector.Last(), 3);
}

TEST_F(StaticVectorTest, ForwardIteratorTest) {
	StaticVector<int, 5> staticVector;

	staticVector.PushBack(1);
	staticVector.PushBack(2);
	staticVector.PushBack(3);

	StaticVectorIterator<int, 5> staticVectorIterator = staticVector.GetIterator();
	int i = 0;
	while (staticVectorIterator.HasNext()) {
		i++;
		EXPECT_EQ(staticVectorIterator.Next(), i);
	}
}

TEST_F(StaticVectorTest, BackwardIteratorTest) {
	StaticVector<int, 5> staticVector;

	staticVector.PushBack(1);
	staticVector.PushBack(2);
	staticVector.PushBack(3);

	StaticVectorIterator<int, 5> staticVectorIterator = staticVector.End();
	int i = 3;
	while (staticVectorIterator.HasPrev()) {
		EXPECT_EQ(staticVectorIterator.Prev(), i);
		i--;
	}
}

void RunStaticVectorTests() {
	::testing::InitGoogleTest();
	RUN_ALL_TESTS();
}