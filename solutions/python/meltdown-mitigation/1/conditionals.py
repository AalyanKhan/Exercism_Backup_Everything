"""Functions to prevent a nuclear meltdown."""


def is_criticality_balanced(temperature, neutrons_emitted):
    """Verify criticality is balanced.

    Parameters:
        temperature (int or float): The temperature value in kelvin.
        neutrons_emitted (int or float): The number of neutrons emitted per second.

    Returns:
        bool: Is criticality balanced?
    """
    return (
        temperature < 800
        and neutrons_emitted > 500
        and (temperature * neutrons_emitted) < 500000
    )


def reactor_efficiency(voltage, current, theoretical_max_power):
    """Assess reactor efficiency zone.

    Parameters:
        voltage (int or float): Voltage value.
        current (int or float): Current value.
        theoretical_max_power (int or float): The power level that corresponds to a 100% efficiency.

    Returns:
        str: One of ('green', 'orange', 'red', or 'black').
    """
    generated_power = voltage * current
    result = (generated_power / theoretical_max_power) * 100

    if result >= 80:
        return "green"
    elif result >= 60:
        return "orange"
    elif result >= 30:
        return "red"
    else:
        return "black"


def fail_safe(temperature, neutrons_produced_per_second, threshold):
    """Assess and return status code for the reactor.

    Parameters:
        temperature (int or float): The value of the temperature in kelvin.
        neutrons_produced_per_second (int or float): The neutron flux.
        threshold (int or float): The threshold for the category.

    Returns:
        str: One of ('LOW', 'NORMAL', 'DANGER').
    """
    product = temperature * neutrons_produced_per_second

    low_bound = 0.9 * threshold
    high_bound = 1.1 * threshold

    if product < low_bound:
        return "LOW"
    elif low_bound <= product <= high_bound:
        return "NORMAL"
    else:
        return "DANGER"