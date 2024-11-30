	static *buffer[open_max][buffer_size];
	char		*new_line;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > OPEN_MAX)
		return (NULL);
	if ((str[fd] && !ft_strchr(str[fd], '\n')) || !str[fd])
		new_line = read_buffer(fd, buffer[fd]);
	if (!new_line)
		return (NULL);
	new_line = fetch_line(new_line);
	if (!new_line)
		return (clean_buffer(buffer));
	buffer = clean_buffer(buffer([fd]));
	return (new_line);

lukee bufferin verran
read_buffer:
while (nb_read > 0 && !ft_strchr(buffer, '\n'))
	nb_read = read(fd, buffer, BUFFER_SIZE);
	if (nb_read <= 0)
		break ;
	new_line = append(new_line, buffer);
	if (!new_line)
		break ;
if (nb_read == -1)
{
	clean_buffer(buffer);
	return (free(&newline));
}
else
	return (new_line);

append(new_line, buffer)
{
	char *joined_string;
	int	i;
	int	j;
	if (!new_line)
		new_line = ft_calloc(1,1);
		if (!new_line)
			return (NULL);
	i = ft_strlen(new_line);
	while (buffer[i])
		if (buffer[i] == '\n')
			i++;
			break ;
		i++;

}

-> jos /n
-> append
