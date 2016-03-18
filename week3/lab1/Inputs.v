module inputs(clk, btn_enter, btn_stop, btn_reset,sw_in, sw_out, enter, stop, rst);

input clk, btn_enter, btn_stop, btn_reset;
input [9:0] sw_in;
output enter, stop, rst;
output [9:0]sw_out;

assign sw_out = sw_in;

button_debouncer bd_ent(clk, 1, !btn_enter, enter);
button_debouncer bd_stop(clk, 1, !btn_stop, stop);
button_debouncer bd_rst(clk, 1, !btn_reset, rst);

endmodule