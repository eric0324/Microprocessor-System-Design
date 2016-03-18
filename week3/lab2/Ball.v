module ball(clk, direction, halt,rst,owner,position, outside, win);

input clk;
input direction;
input halt;
input rst;
input owner;

output reg outside;
output reg win;
output reg[9:0]position;

reg[1:0]out;
integer i;

initial begin
for(i=9;i>0;i=i-1)
	position[i]=0;
position[0]=1;

out=0;
outside=0;
end 


//p1:1 p2:0
always@(posedge clk or posedge rst) begin
	if(rst)begin
		outside = 0;
		out=0;
		if(owner)begin
			for(i=9;i>0;i=i-1)
				position[i]=0;
			position[0]=1;
		end else if(owner==0)begin
			for(i=9;i>0;i=i-1)
				position[i]=0;
			position[9]=1;
		end
	end else begin
		if(!halt) begin
			if(direction) begin
				position[9]<=0;
				position[8]<=position[9];
				position[7]<=position[8];
				position[6]<=position[7];
				position[5]<=position[6];
				position[4]<=position[5];
				position[3]<=position[4];
				position[2]<=position[3];
				position[1]<=position[2];
				position[0]<=position[1];
				out[0]<=position[0];
			end else if(direction==0)begin
				out[1]<=position[9];
				position[9]<=position[8];
				position[8]<=position[7];
				position[7]<=position[6];
				position[6]<=position[5];
				position[5]<=position[4];
				position[4]<=position[3];
				position[3]<=position[2];
				position[2]<=position[1];
				position[1]<=position[0];
				position[0]<=0;
			end
		end
		
		
		if(out[0]) begin
			outside=1;
			win=0;
		end else if(out[1]) begin
			outside=1;
			win=1;
		end
	end
end

endmodule