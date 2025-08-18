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

MEASURE(TimeControlMeasure, TransitionCheck0001UF1) {
  heuristic::time_control_with_annealing<1900, 100, 10, 1> control;
  Start();
  for (int i = 0; i < 100'000; ++i) {
    for (int j = 0; j < 1; ++j) {
      MEASURE_DUMMY(control.transition_check(-50));
    }
    static_cast<bool>(control);
  }
  Stop();
}

MEASURE(TimeControlMeasure, TransitionCheck0001UF10) {
  heuristic::time_control_with_annealing<1900, 100, 10, 10> control;
  Start();
  for (int i = 0; i < 100'000; ++i) {
    for (int j = 0; j < 1; ++j) {
      MEASURE_DUMMY(control.transition_check(-50));
    }
    static_cast<bool>(control);
  }
  Stop();
}

MEASURE(TimeControlMeasure, TransitionCheck0001UF100) {
  heuristic::time_control_with_annealing<1900, 100, 10, 100> control;
  Start();
  for (int i = 0; i < 100'000; ++i) {
    for (int j = 0; j < 1; ++j) {
      MEASURE_DUMMY(control.transition_check(-50));
    }
    static_cast<bool>(control);
  }
  Stop();
}

MEASURE(TimeControlMeasure, TransitionCheck0010UF1) {
  heuristic::time_control_with_annealing<1900, 100, 10, 1> control;
  Start();
  for (int i = 0; i < 100'000; ++i) {
    for (int j = 0; j < 10; ++j) {
      MEASURE_DUMMY(control.transition_check(-50));
    }
    static_cast<bool>(control);
  }
  Stop();
}

MEASURE(TimeControlMeasure, TransitionCheck0010UF10) {
  heuristic::time_control_with_annealing<1900, 100, 10, 10> control;
  Start();
  for (int i = 0; i < 100'000; ++i) {
    for (int j = 0; j < 10; ++j) {
      MEASURE_DUMMY(control.transition_check(-50));
    }
    static_cast<bool>(control);
  }
  Stop();
}

MEASURE(TimeControlMeasure, TransitionCheck0010UF100) {
  heuristic::time_control_with_annealing<1900, 100, 10, 100> control;
  Start();
  for (int i = 0; i < 100'000; ++i) {
    for (int j = 0; j < 10; ++j) {
      MEASURE_DUMMY(control.transition_check(-50));
    }
    static_cast<bool>(control);
  }
  Stop();
}

MEASURE(TimeControlMeasure, TransitionCheck0100UF1) {
  heuristic::time_control_with_annealing<1900, 100, 10, 1> control;
  Start();
  for (int i = 0; i < 100'000; ++i) {
    for (int j = 0; j < 100; ++j) {
      MEASURE_DUMMY(control.transition_check(-50));
    }
    static_cast<bool>(control);
  }
  Stop();
}

MEASURE(TimeControlMeasure, TransitionCheck0100UF10) {
  heuristic::time_control_with_annealing<1900, 100, 10, 10> control;
  Start();
  for (int i = 0; i < 100'000; ++i) {
    for (int j = 0; j < 100; ++j) {
      MEASURE_DUMMY(control.transition_check(-50));
    }
    static_cast<bool>(control);
  }
  Stop();
}

MEASURE(TimeControlMeasure, TransitionCheck0100UF100) {
  heuristic::time_control_with_annealing<1900, 100, 10, 100> control;
  Start();
  for (int i = 0; i < 100'000; ++i) {
    for (int j = 0; j < 100; ++j) {
      MEASURE_DUMMY(control.transition_check(-50));
    }
    static_cast<bool>(control);
  }
  Stop();
}

MEASURE(TimeControlMeasure, TransitionCheck1000UF1) {
  heuristic::time_control_with_annealing<1900, 100, 10, 1> control;
  Start();
  for (int i = 0; i < 100'000; ++i) {
    for (int j = 0; j < 1'000; ++j) {
      MEASURE_DUMMY(control.transition_check(-50));
    }
    static_cast<bool>(control);
  }
  Stop();
}

MEASURE(TimeControlMeasure, TransitionCheck1000UF10) {
  heuristic::time_control_with_annealing<1900, 100, 10, 10> control;
  Start();
  for (int i = 0; i < 100'000; ++i) {
    for (int j = 0; j < 1'000; ++j) {
      MEASURE_DUMMY(control.transition_check(-50));
    }
    static_cast<bool>(control);
  }
  Stop();
}

MEASURE(TimeControlMeasure, TransitionCheck1000UF100) {
  heuristic::time_control_with_annealing<1900, 100, 10, 100> control;
  Start();
  for (int i = 0; i < 100'000; ++i) {
    for (int j = 0; j < 1'000; ++j) {
      MEASURE_DUMMY(control.transition_check(-50));
    }
    static_cast<bool>(control);
  }
  Stop();
}
