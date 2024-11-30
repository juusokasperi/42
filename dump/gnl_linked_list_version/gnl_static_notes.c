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
	line = append(line, buffer);
	if (!line)
		break ;
if (nb_read == -1)
{
	clean_buffer(buffer);
	return (free(&line));
}
else
	return (line);

append(line, buffer)
{
	char *joined_string;
	int	i;
	int	j;
	if (!line)
		line = ft_calloc(1,1);
		if (!line)
			return (NULL);
	i = ft_strlen(line);
	j = 0;
	while (buffer[j])
		if (buffer[j] == '\n')
			j++;
			break ;
		j++;
	joined_string = ft_memcpy(joined_string, line, i);
	joined_string = ft_memcpy(joined_string + i, buffer, j);
	ft_free(&line);
	return (joined_string);
}

clean_buffer(buffer)
{
	int i;

	i = 0;
	while (buffer[i] && i < BUFFER_SIZE)
		if (buffer[i] == '\n')
			i++;
			break;
		i++;
	ft_memmove(buffer + i, buffer, length?);
}

enta jos bufferiin luettu vahemman kuin buffer_size? pitasko buffer tayttaa aina nollilla?

