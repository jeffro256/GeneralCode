package jeffrey_ryan.gamecore2d.physics;

import jeffrey_ryan.gamecore2d.node.GameNode;

public class PhysicsBody {
	public GameNode node;
	public Vector2D vel;
	public Vector2D accel;
	public double mass;
	public double restitution;
	
	public PhysicsBody(GameNode node, Vector2D vel, Vector2D accel, double mass, double restitution) {
		if (vel == null) throw new IllegalArgumentException("vel == null");
		if (accel == null) throw new IllegalArgumentException("accel == null");
		if (mass == 0) throw new IllegalArgumentException("mass == 0");
		
		this.node = node;
		this.vel = vel;
		this.accel = accel;
		this.mass = mass;
		this.restitution = restitution;
	}
	
	public PhysicsBody() {
		this(null, new Vector2D(), new Vector2D(), 1, 1);
	}
	
	public void applyForce(Vector2D force) {
		accel.add(force.over(mass));
	}
	
	public void applyImpluse(Vector2D impluse) {
		vel.add(impluse.over(mass));
	}
	
	public void update(double seconds) {
		vel.add(accel.times(seconds));
	    node.pos.add(vel.times(seconds).plus(accel.times(seconds).times(seconds).over(2)));
	    accel.multiply(0);
	}
}
