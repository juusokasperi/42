/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrinta- <jrinta-@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 13:43:17 by phuocngu          #+#    #+#             */
/*   Updated: 2025/05/22 16:23:21 by jrinta-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "mini_rt.h"

typedef struct s_line_context
{
	char	*line;
	int		idx;
	bool	is_checkered;
	float	scale;
	t_rgb	color_2;
	t_data	*data;
}	t_line_context;

/* Main parsing functions */
bool	parse_scene(const char *filename, t_data *data);
bool	validate_scene_file(const char *filename, int *fd);
bool	parse_identifier(char *line, char **identifier, t_line_context *ctx);

/* Scene element parsing functions */
bool	validate_scene_content(t_data *data);
bool	allocate_scene_memory(t_data *data);
bool	cleanup(t_data *data);
bool	parse_ambient(char *line, t_data *data);
bool	parse_camera(char *line, t_data *data);
bool	parse_light(char *line, t_data *data);

/* Object parsing functions */
bool	parse_sphere(char *line, t_line_context *ctx);
bool	parse_plane(char *line, t_line_context *ctx);
bool	parse_cylinder(char *line, t_line_context *ctx);
bool	parse_cone(char *line, t_line_context *ctx);
bool	validate_object_count(t_data *data);

/* Object property parsing utilities */
bool	parse_object_position(char **parts, t_vector *position);
bool	parse_object_direction(char **parts, t_vector *direction);
bool	parse_object_color(char *color_str, t_object *object,
			bool is_checkered, t_rgb *color_2);
void	setup_checkered_object(t_object *obj, t_line_context *ctx);

/* Common parsing utilities */
bool	validate_parts_count(char **parts, int expected_count, char *obj_name);
bool	validate_and_init_object(t_data *data, t_object **obj,
			char **parts, t_shape type);
bool	parse_positive_float(char **parts, int index, float *value,
			char *error_msg);
bool	validate_range_float(float value, float min,
			float max, char *param_name);
bool	parse_ratio(char **parts, int index, float *ratio, char *param_name);
bool	parse_fov(char **parts, int index, int *fov);

/* Basic parsing functions */
bool	parse_float(char *str, float *result);
bool	parse_vector(char *str, t_vector *vec);
bool	parse_normalized_vector(char *str, t_vector *vec);
bool	parse_rgb(char *str, t_rgb *color);
bool	parse_dual_rgb(char *str, t_rgb *color_1, t_rgb *color_2);

/* String utilities */
void	free_split(char **arr);
char	**ft_split_isspace(char const *s);
bool	trim_line(char **line);

#endif
