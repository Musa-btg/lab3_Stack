#define RPN_TESTING
#include "../src/main.cpp"
#include <gtest/gtest.h>
#include <string>

// ==================== priority ====================
TEST(PriorityTest, AddSub) {
    EXPECT_EQ(priority('+'), 1);
    EXPECT_EQ(priority('-'), 1);
}
TEST(PriorityTest, MulDiv) {
    EXPECT_EQ(priority('*'), 2);
    EXPECT_EQ(priority('/'), 2);
}
TEST(PriorityTest, Unknown) {
    EXPECT_EQ(priority('('), -1);
    EXPECT_EQ(priority('a'), -1);
}

// ==================== RPN (с пробелами) ====================
TEST(RPNTest, SimpleAddition) {
    std::string in = "2+3";
    EXPECT_EQ(RPN(in), "2 3 + ");
}
TEST(RPNTest, SimpleSubtraction) {
    std::string in = "5-2";
    EXPECT_EQ(RPN(in), "5 2 - ");
}
TEST(RPNTest, MulDiv) {
    std::string in = "6*4";
    EXPECT_EQ(RPN(in), "6 4 * ");
    std::string in2 = "8/2";
    EXPECT_EQ(RPN(in2), "8 2 / ");
}
TEST(RPNTest, Priority) {
    std::string in = "2+3*4";
    EXPECT_EQ(RPN(in), "2 3 4 * + ");
}
TEST(RPNTest, LeftAssociativity) {
    std::string in = "8-2-3";
    EXPECT_EQ(RPN(in), "8 2 - 3 - ");
}
TEST(RPNTest, Parentheses) {
    std::string in = "(2+3)*4";
    EXPECT_EQ(RPN(in), "2 3 + 4 * ");
}
TEST(RPNTest, NestedParentheses) {
    std::string in = "((2+3)*4)-5";
    EXPECT_EQ(RPN(in), "2 3 + 4 * 5 - ");
}
TEST(RPNTest, WithSpaces) {
    std::string in = "2 + 3 * 4";
    EXPECT_EQ(RPN(in), "2 3 4 * + ");
}
TEST(RPNTest, SingleDigit) {
    std::string in = "7";
    EXPECT_EQ(RPN(in), "7 ");
}

// ==================== RPN: многозначные числа ====================
TEST(RPNTest, MultiDigitSub) {
    std::string in = "52-6-7";
    EXPECT_EQ(RPN(in), "52 6 - 7 - ");
}
TEST(RPNTest, MultiDigitMixed) {
    std::string in = "12+34*2";
    EXPECT_EQ(RPN(in), "12 34 2 * + ");
}
TEST(RPNTest, MultiDigitParen) {
    std::string in = "(12+3)*4";
    EXPECT_EQ(RPN(in), "12 3 + 4 * ");
}

// ==================== answer (ОПЗ с пробелами) ====================
TEST(AnswerTest, Add) {
    std::string rpn = "2 3 + ";
    EXPECT_DOUBLE_EQ(answer(rpn), 5.0);
}
TEST(AnswerTest, SubOrder) {
    std::string rpn = "5 2 - ";
    EXPECT_DOUBLE_EQ(answer(rpn), 3.0);
}
TEST(AnswerTest, Mul) {
    std::string rpn = "6 4 * ";
    EXPECT_DOUBLE_EQ(answer(rpn), 24.0);
}
TEST(AnswerTest, Div) {
    std::string rpn = "8 2 / ";
    EXPECT_DOUBLE_EQ(answer(rpn), 4.0);
}
TEST(AnswerTest, DivFraction) {
    std::string rpn = "1 4 / ";
    EXPECT_DOUBLE_EQ(answer(rpn), 0.25);
}
TEST(AnswerTest, PriorityExpression) {
    std::string rpn = "2 3 4 * + ";   // 2 + 3*4
    EXPECT_DOUBLE_EQ(answer(rpn), 14.0);
}
TEST(AnswerTest, Nested) {
    std::string rpn = "2 3 + 4 * 5 - ";   // (2+3)*4 - 5
    EXPECT_DOUBLE_EQ(answer(rpn), 15.0);
}
TEST(AnswerTest, MultiDigit) {
    std::string rpn = "52 6 - 7 - ";
    EXPECT_DOUBLE_EQ(answer(rpn), 39.0);
}
TEST(AnswerTest, BigNumbers) {
    std::string rpn = "100 5 / 3 - ";
    EXPECT_DOUBLE_EQ(answer(rpn), 17.0);
}

// ==================== Интеграция ====================
TEST(IntegrationTest, FullPipeline) {
    std::string expr = "(2+3)*4-5";
    std::string rpn = RPN(expr);
    EXPECT_EQ(rpn, "2 3 + 4 * 5 - ");
    EXPECT_DOUBLE_EQ(answer(rpn), 15.0);
}
TEST(IntegrationTest, ComplexExpression) {
    std::string expr = "2+3*4-6/2";
    std::string rpn = RPN(expr);
    EXPECT_DOUBLE_EQ(answer(rpn), 11.0);
}
TEST(IntegrationTest, AllOperations) {
    std::string expr = "((1+2)*3-4)/5";
    std::string rpn = RPN(expr);
    EXPECT_DOUBLE_EQ(answer(rpn), 1.0);
}
TEST(IntegrationTest, MultiDigit) {
    std::string expr = "52-6-7";
    std::string rpn = RPN(expr);
    EXPECT_DOUBLE_EQ(answer(rpn), 39.0);
}
TEST(IntegrationTest, BigNumbers) {
    std::string expr = "100/5-3";
    std::string rpn = RPN(expr);
    EXPECT_DOUBLE_EQ(answer(rpn), 17.0);
}

// ==================== TStack ====================
TEST(StackTest, PushPopPeek) {
    TStack<int> s;
    EXPECT_TRUE(s.IsEmpty());
    s.Push(1); s.Push(2); s.Push(3);
    EXPECT_EQ(s.size(), 3u);
    EXPECT_EQ(s.Peek(), 3);
    EXPECT_EQ(s.Pop(), 3);
    EXPECT_EQ(s.Pop(), 2);
    EXPECT_EQ(s.Pop(), 1);
    EXPECT_TRUE(s.IsEmpty());
}
TEST(StackTest, PopEmptyThrows) {
    TStack<int> s;
    EXPECT_THROW(s.Pop(), std::out_of_range);
}
TEST(StackTest, CopyConstructor) {
    TStack<int> a;
    a.Push(10); a.Push(20);
    TStack<int> b = a;
    EXPECT_EQ(b.size(), 2u);
    EXPECT_EQ(b.Peek(), 20);
    b.Pop();
    EXPECT_EQ(a.size(), 2u);
}