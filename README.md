# STM32 Telegraph

Write morse code on a 16x2 LCD display using button presses. This project doesn't use GPIO interrupts to make things more challenging.

## Wiring 

## Usage
The lights indicate when an action has been made or cancelled.

- Short presses means dot, blue light quickly turns on and off (100ms).
- Long presses means dash, blue light turns on and off for 500ms.
- If the morse code entered in wrong, the red light blinks for 250ms.
- If more than 3 seconds elapse since the last command, the command stack is cleared and the red light blinks for 250ms.

## Examples
