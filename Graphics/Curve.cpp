#include "Curve.h"

Curve::Curve()
{
}

Curve::~Curve()
{
}

void Curve::init()
{
	this->control_points_pos = {
		{ 0.0, 8.5, -2.0 },
		{ -3.0, 11.0, 2.3 },
		{ -6.0, 8.5, -2.5 },
		{ -4.0, 5.5, 2.8 },
		{ 1.0, 2.0, -4.0 },
		{ 4.0, 2.0, 3.0 },
		{ 7.0, 8.0, -2.0 },
		{ 3.0, 10.0, 3.7 }
	};
}

void Curve::calculate_curve()
{
	for (unsigned int i = 0; i < control_points_pos.size(); ++i)
	{
		glm::mat4x3 p_value_matrix = glm::mat4x3(
			control_points_pos[(i == 0) ? control_points_pos.size() - 1:i-1],
			control_points_pos[i],
			control_points_pos[(i+1) % control_points_pos.size()],
			control_points_pos[(i+2) % control_points_pos.size()]
		);

		for (float u = 0; u <= 1.0; u = u + (1.0 / num_points_per_segment))
		{
			glm::vec4 u_value_vector = glm::vec4(glm::pow(u, 3), glm::pow(u, 2), u, 1.0);
			this->curve_points_pos.push_back(tau * p_value_matrix * catmull_matrix * u_value_vector);
		}
	}
}
