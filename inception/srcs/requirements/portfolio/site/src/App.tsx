import { useReducer } from 'react';
import { projects, Project } from './data/projects';
import { FilterState, FilterAction } from './types';

import { ContainerDiv, Link, Footer } from './styled'

import Header from './components/Header'
import DropDown from './components/DropDown'
import ProjectCard from './components/ProjectCard'

const initialState: FilterState = { filter: 'ALL', filteredProjects: projects };

const filterReducer = (state: FilterState, action: FilterAction): FilterState => {
  switch (action.type) {
    case 'SET_FILTER':
      const filteredProjects = action.payload === 'ALL'
        ? projects
        : projects.filter((project: Project) => project.languages.includes(action.payload)
          );
      return { filter: action.payload, filteredProjects };
    default:
      return state;
  }
};

const useProjectFilter = () => {
  const [state, dispatch] = useReducer(filterReducer, initialState);
  return { ...state, dispatch };
};

const App = () => {
  const { filteredProjects, dispatch } = useProjectFilter();

  return (
    <ContainerDiv>
      <Header />
      <DropDown dispatch={dispatch}/>
      <div className="projects-grid">
        {filteredProjects.map(project => (
          <ProjectCard key={project.id} project={project} />
        ))}
      </div>
      <Footer>
        © JR 2025{" | "}
        <Link href="https://www.github.com/juusokasperi" target="_blank">Git</Link>
      </Footer>
    </ContainerDiv>
  );
};

export default App
