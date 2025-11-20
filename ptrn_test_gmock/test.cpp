#include "pch.h"



extern "C" {
#include <stdio.h>   // for sprintf

#include "states_semaforo_default.h" // определ€ем тут StateSemaforoPtr, StateSemEvents
#include "states_semaforo_implement.h"
#include "states_semaforo_internal.h"
// состо€ние
#include "state_yellow.h"
    // завершение объ€влени€
    struct SemaforoMaker {
        long tickTimeWork;
        struct StateSemaforo state;
    };

    extern SemaforoMakerPtr _instance;
}
namespace BaseTestGmockNamespace {

    TEST(TestCaseName, TestNameDymmy) {
        EXPECT_EQ(1, 1);
        EXPECT_TRUE(true);
    }

    class MockTestFirst {
    public:
        MOCK_METHOD(void, SomeMethod, ());
    };

    TEST(TestCaseName, TestName) {
        MockTestFirst mock;
        EXPECT_CALL(mock, SomeMethod);
        mock.SomeMethod();
        EXPECT_EQ(1, 1);
        EXPECT_TRUE(true);
    }

    TEST(SemaforoTest, Test_04_StateFunctionsNotNull) {
        SemaforoMakerPtr semaforo = createSemaforo();

        EXPECT_NE(semaforo->state.state_yellow, nullptr);
        EXPECT_NE(semaforo->state.state_red, nullptr);
        EXPECT_NE(semaforo->state.state_red_yellow, nullptr);
        EXPECT_NE(semaforo->state.state_green, nullptr);
        EXPECT_NE(semaforo->state.state_green_blink, nullptr);
        EXPECT_NE(semaforo->state.state_yellow_blink, nullptr);

        destroySemaforo(semaforo);
    }


    class MockTest {
    public:
        MOCK_METHOD(void, on_entry, (), ());
        MOCK_METHOD(void, on_do, (), ());
        MOCK_METHOD(void, on_exit, (), ());
        MOCK_METHOD(long, check_change_state, (), ());
    };
    static MockTest* g_mock = nullptr;

    static void c_on_entry() { g_mock->on_entry(); }
    static void c_on_do() { g_mock->on_do(); }
    static void c_on_exit() { g_mock->on_exit(); }
    static long c_check_change_state() { return g_mock->check_change_state(); }

    // чтобы не писать testing::
    //using testing::InSequence;
    //using testing::Return;

    TEST(YellowStateTest, SwitchToRedWhenTimeout)
    {
        MockTest mock;
        g_mock = &mock;

        //EXPECT_CALL(mock, check_change_state())
        //    .WillOnce(::testing::Return(10))
        //    .WillOnce(::testing::Return(20));
        // ќписываем пор€док вызова. »менно тот ожидаемый пор€док
        // который будет при выполнении.
        {
            testing::InSequence seq; // чтобы видеть пор€док
            EXPECT_CALL(mock, on_entry());

            // первый раз возвращает 0, почему-то
            EXPECT_CALL(mock, check_change_state())     // #1
                .WillOnce(testing::Return(16));

            EXPECT_CALL(mock, on_do());

            EXPECT_CALL(mock, check_change_state())     // #2
                .WillOnce(testing::Return(20));

            EXPECT_CALL(mock, on_exit());
            //EXPECT_CALL(mock, on_exit()); // покажет что не вызываетс€.
            //EXPECT_CALL(mock, on_do()).Times(1);
        }
        StateSemaforo s{};
        transitionToYellow(&s);

        StateSemEvents events{
            .on_entry = c_on_entry,
            .on_do = c_on_do,
            .on_exit = c_on_exit,
            .check_change_state = c_check_change_state,
            .workTimeToSwitch = 3 
        };

        s.state_yellow(&s, events);

        ASSERT_STREQ(s.name, "red_state");
    }
}

int main(int argc, char** argv) {
    ::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}