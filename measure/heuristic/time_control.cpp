#include "competitive/heuristic/time_control.hpp"
#include <measurement.hpp>

MEASURE(TimeControlMeasure, UpdateFrequency1) {
  heuristic::time_control_t<1900, 1> control;
  Start();
  for (int i = 0; i < 1'000'000; ++i) {
    MEASURE_DUMMY(static_cast<bool>(control));
  }
  Stop();
}

MEASURE(TimeControlMeasure, UpdateFrequency10) {
  heuristic::time_control_t<1900, 10> control;
  Start();
  for (int i = 0; i < 1'000'000; ++i) {
    MEASURE_DUMMY(static_cast<bool>(control));
  }
  Stop();
}

MEASURE(TimeControlMeasure, UpdateFrequency100) {
  heuristic::time_control_t<1900, 100> control;
  Start();
  for (int i = 0; i < 1'000'000; ++i) {
    MEASURE_DUMMY(static_cast<bool>(control));
  }
  Stop();
}

MEASURE(TimeControlMeasure, TransitionCheckForShort1) {
  heuristic::time_control_with_annealing<1900, 100, 10, 1> control;
  Start();
  for (int i = 0; i < 1'000'000; ++i) {
    MEASURE_DUMMY(control.transition_check(-50));
    static_cast<bool>(control);
  }
  Stop();
}

MEASURE(TimeControlMeasure, TransitionCheckForShort10) {
  heuristic::time_control_with_annealing<1900, 100, 10, 10> control;
  Start();
  for (int i = 0; i < 1'000'000; ++i) {
    MEASURE_DUMMY(control.transition_check(-50));
    static_cast<bool>(control);
  }
  Stop();
}

MEASURE(TimeControlMeasure, TransitionCheckForShort100) {
  heuristic::time_control_with_annealing<1900, 100, 10, 100> control;
  Start();
  for (int i = 0; i < 1'000'000; ++i) {
    MEASURE_DUMMY(control.transition_check(-50));
    static_cast<bool>(control);
  }
  Stop();
}

MEASURE(TimeControlMeasure, TransitionCheckForLong1) {
  heuristic::time_control_with_annealing<1900, 100, 10, 1> control;
  Start();
  for (int i = 0; i < 1'000'000; ++i) {
    MEASURE_DUMMY(control.transition_check(-50));
    static_cast<bool>(control);
  }
  Stop();
}

MEASURE(TimeControlMeasure, TransitionCheckForLong10) {
  heuristic::time_control_with_annealing<1900, 100, 10, 10> control;
  Start();
  for (int i = 0; i < 1'000'000; ++i) {
    MEASURE_DUMMY(control.transition_check(-50));
    static_cast<bool>(control);
  }
  Stop();
}

MEASURE(TimeControlMeasure, TransitionCheckForLong100) {
  heuristic::time_control_with_annealing<1900, 100, 10, 100> control;
  Start();
  for (int i = 0; i < 1'000'000; ++i) {
    MEASURE_DUMMY(control.transition_check(-50));
    static_cast<bool>(control);
  }
  Stop();
}
